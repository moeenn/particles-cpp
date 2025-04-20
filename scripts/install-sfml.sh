#! /bin/bash

SFML_VERSION="3.0.0"
FILE_NAME="SFML-${SFML_VERSION}"
SFML_URL="https://www.sfml-dev.org/files/${FILE_NAME}-linux-gcc-64-bit.tar.gz";

# download SFML dependency if required.
if [[ -f "./${FILE_NAME}.tar.gz" ]]; then
  echo "SFML archive already downloaded. Skipping download";
else
  echo "Downloading SFML";
  COMMAND="curl --output ./${FILE_NAME}.tar.gz ${SFML_URL}";
  eval $COMMAND;
fi

# extract downloaded archive.
mkdir -p ./vendor/$FILE_NAME;
tar -xvzf ./$FILE_NAME.tar.gz -C ./vendor;
