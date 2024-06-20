#!/bin/sh

DEPENDENCIES="deps.txt"

echo "Installing Dependencies"

echo "Finding dependencies in $DEPENDENCIES"
if [ ! -f "$DEPENDENCIES" ]; then
    echo "No dependency file $DEPENDENCIES"
    exit 1
fi

exit_status=0

while IFS= read -r dependency; do
    echo "Installing $dependency with apt"

    while true; do
        err=$(apt install -y $dependency 2>&1 | grep -s "E:")

        if [ -n "$err" ]; then
            echo "apt failed to install $dependency. $err" >> /var/log/require.log
            echo "Failed to install $dependency. Skipping!"
            trap "echo Failed to install package $dependency" EXIT
            exit_status=2
            break

        else
            echo "Successfullying installed $dependency"
            echo ""
            break
        fi
    done
done < "$DEPENDENCIES"

echo "Finished."
exit $exit_status
