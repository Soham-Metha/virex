# "download the syntax highligher theme"

if [ -d "$HOME/.var/app/com.visualstudio.code" ]; then
    printf "\e[36m		[ DETECTED VS CODE ]\t: [ FLATPAK ] \e[0m\n\n"
    cp -r ./tools/themes/vs_code/sasm_syntax_highlight/ ~/.var/app/com.visualstudio.code/data/vscode/extensions/
elif [ -d "$HOME/.vscode/extensions" ]; then
    printf "\e[36m		[ DETECTED VS CODE ]\t: [ NATIVE ] \e[0m\n\n"
    cp -r ./tools/themes/vs_code/sasm_syntax_highlight/ ~/.vscode/extensions/
else
    printf "\e[31m		[ DETECTED VS CODE ]\t: [ NOT FOUND ] \e[0m\n\n"
fi

printf "\e[33m		[ VIREX BUILD STARTED ] \e[0m\n\n"
make virex

printf "\e[33m		[ SUDO NEEDED ] \e[0m\n\n"
printf "\e[36m		[ SYSTEM INSTALL ]\t: [ VIREX BINARIES ] \e[0m\n\n"

# move the executables to bin so that they can be used as regular commands
sudo mv ./build/virex /usr/local/bin/
sudo mv ./build/sasm /usr/local/bin/
sudo mv ./build/orin /usr/local/bin/
