
build_hc(){
    if [ -d ./build/ ]; then
        rm -rf ./build/
    fi

    cmake -B build
    cmake --build build/
    cp src/*.glade build/
    exit 0
}

if [ "$1" = "--rebuild" ]; then 
    build_hc
fi

USR_HOME=$(getent passwd $SUDO_USER | cut -d: -f6)

echo "Default scripts directory is $USR_HOME/house-controller/scripts"
echo "Which directory should scripts be help in? (enter for default)"
read script_dir

if [ -z "$script_dir" ]; then
    mkdir -p "$USR_HOME/house-controller/scripts" && \
    script_dir="$USR_HOME/house-controller/scripts"

elif [ ! -d "$script_dir" ]; then
    echo "Directory $script_dir not found. Create? (y/n)"
    read create_dir_a

    if [ "$create_dir_a" = "y" ]; then
        mkdir -p "$script_dir"
    else
        exit 2
    fi
fi 

tmp_dir="/var/tmp/house-controller"

echo "Using $script_dir"

mkdir -p "$tmp_dir"
echo "$script_dir" > "$tmp_dir"/script.dir_txt
echo "$(pwd)" > "$tmp_dir"/hc_home.dir_txt

build_hc
echo "Done."
