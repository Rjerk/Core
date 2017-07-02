echo "---install p7zip---";
sudo apt-get -y install p7zip-full p7zip-rar

echo "---install boost---";
sudo apt-get -y install libboost-all-dev

echo "---install vim---";
sudo apt-get -y install vim

echo "---install git---";
sudo apt-get -y install git

echo "---install k-vim dependency---";
sudo apt-get install exuberant-ctags
sudo apt-get install build-essential cmake python-dev
sudo apt-get install silversearcher-ag

sudo apt-get install -y python-pip

sudo pip install --upgrade pip

sudo pip install pyflakes
sudo pip install pylint
sudo pip install pep8

sudo apt-get install nodejs npm
sudo npm install -g jslint
sudo npm install jshint -g

sudo apt-get install -y curl
curl -sL https://deb.nodesource.com/setup_7.x | sudo -E bash -
sudo apt-get install -y nodejs
sudo apt-get install -y build-essential

echo "---install hexo---";
sudo npm isntall -g hexo-cli

echo "---install sublime text3---";
wget -qO - https://download.sublimetext.com/sublimehq-pub.gpg | sudo apt-key add -
echo "deb https://download.sublimetext.com/ apt/dev/" | sudo tee /etc/apt/sources.list.d/sublime-text.list
sudo apt update && sudo apt install -y sublime-text

echo "dependency for nginx"
sudo apt-get -y install libpcre3 libpcre3-dev
sudo apt-get install zlib1g-dev




