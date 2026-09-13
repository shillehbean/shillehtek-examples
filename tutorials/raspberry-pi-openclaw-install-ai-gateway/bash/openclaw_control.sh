# Start, stop, or restart the openclaw-gateway systemd user service and run OpenClaw diagnostic/cron commands.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-openclaw-install-ai-gateway
# Shop parts: https://shillehtek.com
# More examples: https://github.com/shillehbean/shillehtek-examples
#

systemctl --user start openclaw-gateway
  systemctl --user stop openclaw-gateway
  systemctl --user restart openclaw-gateway
  openclaw doctor
  openclaw cron list
