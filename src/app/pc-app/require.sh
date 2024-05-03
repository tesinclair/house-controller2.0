#!/bin/bash

# Build essential should be covered by dockerfile
deps="packages.txt"

echo "Installing Dependencies"

echo "Finding dependencies in $deps"
if [ ! -f "$deps" ]; then
    echo "No dependency file $deps"
    exit 1
fi

while IFS= read -r dep; do
    echo "Installing $dep with apt"

    while true; do
        err=$(apt-get install -y $dep 2>&1 | grep -s 'E:')

        if [[ -n "$err" ]] then
            echo "apt-get failed"
            echo "apt-get failed to install $dep. $err" >> /var/logs/require.log
            echo "Try again?"
            read retry

            if [[ "$retry" == 'y' ]] then
                echo "Retrying..."
                continue
            else
                echo "ABORTING"
                trap "echo Failed to Install Package $dep" EXIT
                exit 1
            fi

        else
            echo "Successfullying installed $dep"
            echo ""
            break
        fi
    done
done < "$deps"

echo "Finished."
exit 0
