# Initialize ns-3 for MTP development

function print {
    MAGENTA="\033[38;5;165;1m"
    RESET="\033[01;00m"
    echo -e "\n$MAGENTA========== $1 ==========$RESET\n"
}

# Required packages
print "Installing Required Packages"
sudo apt update
sudo apt install build-essential cmake -y

# Setup ns-3
print "Setting up ns-3"
cp examples/tutorial/first.cc scratch/first-copy.cc
./ns3 configure --enable-modules core,network,internet,applications,point-to-point,modular-transport
./ns3 build

# Tests
print "Running Simple ns-3 Test"
./ns3 run scratch/first-copy.cc
print "Running mt_test"
./ns3 run scratch/mt_test/mt_test.cc
