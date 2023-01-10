#!/bin/bash

NoColor="\033[0m"
CyanColor="\033[0;36m"
GreenColor="\033[0;32m"


echo -e "\n${CyanColor}Building the project...${NoColor}\n"

mv include/FilePaths.hpp /tmp/FilePaths.hpp
cp include/InstallFilePaths.hpp include/FilePaths.hpp

./autobuild.sh re release

cp /tmp/FilePaths.hpp include/FilePaths.hpp

echo -e "\n${GreenColor}Project builded successfully !${NoColor}\n"


echo -e "\n${CyanColor}Creating binary...${NoColor}\n"

sudo cp ./bomberman /usr/bin/bomberman

echo -e "\n${GreenColor}Binary successfully created !${NoColor}\n"


echo -e "\n${CyanColor}Creating application shortcut...${NoColor}\n"

sudo touch /usr/share/applications/bomberman.desktop
sudo chown `whoami`:`whoami` /usr/share/applications/bomberman.desktop
sudo echo -e "[Desktop Entry]\n\n" > /usr/share/applications/bomberman.desktop
sudo echo -e "Name=Bomberman\n" >> /usr/share/applications/bomberman.desktop
sudo echo -e "GenericName=Bomberman game" >> /usr/share/applications/bomberman.desktop
sudo echo -e "Comment=Bomberman game" >> /usr/share/applications/bomberman.desktop
sudo echo -e "Exec=/usr/bin/bomberman" >> /usr/share/applications/bomberman.desktop
sudo echo -e "Terminal=false" >> /usr/share/applications/bomberman.desktop
sudo echo -e "Keywords=Game" >> /usr/share/applications/bomberman.desktop
sudo echo -e "Icon=/etc/bomberman/assets/Textures/Logo.png" >> /usr/share/applications/bomberman.desktop
sudo echo -e "Type=Application" >> /usr/share/applications/bomberman.desktop
sudo echo -e "Categories=Game;" >> /usr/share/applications/bomberman.desktop

echo -e "\n${GreenColor}Application shortcut created !${NoColor}\n"


echo -e "\n${CyanColor}Creating configuration...${NoColor}\n"

sudo mkdir -p /etc/bomberman/
sudo cp ./.bomberman/Settings.json /etc/bomberman/Settings.json
sudo cp -r ./.bomberman/maps /etc/bomberman/maps
sudo cp -r ./.bomberman/assets /etc/bomberman/assets

sudo chown -R `whoami`:`whoami` /etc/bomberman

for file in /etc/bomberman/maps/*.json
do
    name=$(echo "`basename $file`" | cut -f 1 -d '.')
    echo -e "${CyanColor}Configuring $name map${NoColor}"
    echo -e "`sed 's/\.\/\.bomberman\//\/etc\/bomberman\//g' $file`" > "$file"
done

echo -e "\n${GreenColor}Configuration successfully created !${NoColor}\n"
