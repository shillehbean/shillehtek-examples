# Creates an email options table and sends the email via Xedge's SMTP helper, printing the result in the callback.
#
# Full tutorial: https://shillehtek.com/blogs/news/esp32-xedge-smtp-send-email-securely
# Parts used: https://shillehtek.com/products/xiao-seeed-esp32s3-pre-soldered-with-usb-c-cable
#             https://shillehtek.com/products/xiao-seeed-esp32c3-pre-soldered-with-usb-to-usb-c-cable
#             https://shillehtek.com/products/xiao-seeed-esp32c6-pre-soldered-with-usb-c-cable
# More examples: https://github.com/shillehbean/shillehtek-examples
#

local op={
   to="info@realtimelogic.com",
   subject="Hello",
   body="What's up?"
}
xedge.sendmail(op, function(ok,err) trace(ok,err) end)
