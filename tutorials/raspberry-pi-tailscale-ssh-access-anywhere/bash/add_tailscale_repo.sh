# Adds Tailscale's GPG key and APT repository for Raspbian Buster so the package can be installed from Tailscale's repository.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-tailscale-ssh-access-anywhere
# Shop parts: https://shillehtek.com
# More examples: https://github.com/shillehbean/shillehtek-examples
#

curl -fsSL https://pkgs.tailscale.com/stable/raspbian/buster.gpg | sudo apt-key add -
curl -fsSL https://pkgs.tailscale.com/stable/raspbian/buster.list | sudo tee /etc/apt/sources.list.d/tailscale.list
