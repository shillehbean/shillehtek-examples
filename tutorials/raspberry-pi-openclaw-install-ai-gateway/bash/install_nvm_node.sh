# Install nvm (Node Version Manager), load it into the shell, and install/use Node.js v24.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-openclaw-install-ai-gateway
# Shop parts: https://shillehtek.com
# More examples: https://github.com/shillehbean/shillehtek-examples
#

curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.40.1/install.sh | bash
  source ~/.bashrc   # or restart the terminal
  nvm install 24
  nvm use 24
  node -v            # should show v24.x.x
