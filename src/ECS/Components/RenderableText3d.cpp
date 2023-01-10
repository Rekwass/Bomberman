/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** RenderableText3d
*/

#include "ECS/Components/RenderableText3d.hpp"

#include "Graphic/RessourcesManager.hpp"
#include "rlgl.h"

ecs::component::RenderableText3d::RenderableText3d(std::string_view text, float fontSize, float fontSpacing, float lineSpacing, bool backface, Color color) noexcept :
    font(GetFontDefault()), text(text), fontSize(fontSize), fontSpacing(fontSpacing), lineSpacing(lineSpacing), backface(backface), color(color)
{
    this->needDestroy = true;
}

ecs::component::RenderableText3d::RenderableText3d(std::string_view fontPath, std::string_view text, float fontSize, float fontSpacing, float lineSpacing, bool backface, Color color) noexcept :
    font(graphic::RessourcesManager::getFont(fontPath.data())), text(text), fontSize(fontSize), fontSpacing(fontSpacing), lineSpacing(lineSpacing), backface(backface), color(color)
{
}

ecs::component::RenderableText3d::RenderableText3d(RenderableText3d&& other) noexcept
{
    this->needDestroy = other.needDestroy;
    other.needDestroy = false;
    this->font = other.font;
    this->text = other.text;
    this->fontSize = other.fontSize;
    this->fontSpacing = other.fontSpacing;
    this->lineSpacing = other.lineSpacing;
    this->backface = other.backface;
    this->color = other.color;
}

ecs::component::RenderableText3d& ecs::component::RenderableText3d::operator=(RenderableText3d&& other) noexcept
{
    this->needDestroy = other.needDestroy;
    other.needDestroy = false;
    this->font = other.font;
    this->text = other.text;
    this->fontSize = other.fontSize;
    this->fontSpacing = other.fontSpacing;
    this->lineSpacing = other.lineSpacing;
    this->backface = other.backface;
    this->color = other.color;
    return *this;
}

static void DrawTextCodepoint3D(Font font, int codepoint, utils::Vector position,
    float fontSize, bool backface, Color tint) noexcept
{
    int index = GetGlyphIndex(font, codepoint);
    float scale = fontSize / static_cast<float>(font.baseSize);

    position.x += static_cast<float>(font.glyphs[index].offsetX - font.glyphPadding) / static_cast<float>(font.baseSize) * scale;
    position.z += static_cast<float>(font.glyphs[index].offsetY - font.glyphPadding) / static_cast<float>(font.baseSize) * scale;

    Rectangle srcRec = {font.recs[index].x - static_cast<float>(font.glyphPadding), font.recs[index].y - static_cast<float>(font.glyphPadding), font.recs[index].width + 2.0F * font.glyphPadding, font.recs[index].height + 2.0F * font.glyphPadding};

    float width = (font.recs[index].width + 2.0F * font.glyphPadding) / static_cast<float>(font.baseSize) * scale;
    float height = (font.recs[index].height + 2.0F * font.glyphPadding) / static_cast<float>(font.baseSize) * scale;

    if (font.texture.id > 0) {
        const float x = 0.0F;
        const float y = 0.0F;
        const float z = 0.0F;

        const float tx = srcRec.x / font.texture.width;
        const float ty = srcRec.y / font.texture.height;
        const float tw = (srcRec.x + srcRec.width) / font.texture.width;
        const float th = (srcRec.y + srcRec.height) / font.texture.height;

        rlCheckRenderBatchLimit(4 + 4 * static_cast<int>(backface));
        rlSetTexture(font.texture.id);

        rlPushMatrix();
        rlTranslatef(position.x, position.y, position.z);

        rlBegin(RL_QUADS);
        rlColor4ub(tint.r, tint.g, tint.b, tint.a);

        rlNormal3f(0.0F, 1.0F, 0.0F);
        rlTexCoord2f(tx, ty);
        rlVertex3f(x, y, z);
        rlTexCoord2f(tx, th);
        rlVertex3f(x, y, z + height);
        rlTexCoord2f(tw, th);
        rlVertex3f(x + width, y, z + height);
        rlTexCoord2f(tw, ty);
        rlVertex3f(x + width, y, z);

        if (backface) {
            rlNormal3f(0.0F, -1.0F, 0.0F);
            rlTexCoord2f(tx, ty);
            rlVertex3f(x, y, z);
            rlTexCoord2f(tw, ty);
            rlVertex3f(x + width, y, z);
            rlTexCoord2f(tw, th);
            rlVertex3f(x + width, y, z + height);
            rlTexCoord2f(tx, th);
            rlVertex3f(x, y, z + height);
        }
        rlEnd();
        rlPopMatrix();

        rlSetTexture(0);
    }
}

void ecs::component::RenderableText3d::draw() const noexcept
{
    int length = TextLength(this->text.data());
    float textOffsetY = 0.0F;
    float textOffsetX = 0.0F;
    float scale = this->fontSize / static_cast<float>(this->font.baseSize);

    for (int i = 0; i < length;) {
        int codepointByteCount = 0;
        int codepoint = GetCodepoint(&this->text[i], &codepointByteCount);
        int index = GetGlyphIndex(this->font, codepoint);

        if (codepoint == 0x3f) {
            codepointByteCount = 1;
        }
        if (codepoint == '\n') {
            textOffsetY += scale + this->lineSpacing / static_cast<float>(this->font.baseSize) * scale;
            textOffsetX = 0.0F;
        } else {
            if (this->font.glyphs[index].advanceX == 0) {
                textOffsetX += (this->font.recs[index].width + this->fontSpacing) / static_cast<float>(this->font.baseSize) * scale;
            } else {
                textOffsetX += (this->font.glyphs[index].advanceX + this->fontSpacing) / static_cast<float>(this->font.baseSize) * scale;
            }
        }
        i += codepointByteCount;
    }
}
