# Demonstrate a recursive factorial function in Lua and print the result for a given number.
#
# Full tutorial: https://shillehtek.com/blogs/news/esp32-s3-xedge32-program-lua-web-ide
# Parts used: https://shillehtek.com/products/xiao-seeed-esp32s3-pre-soldered-with-usb-c-cable
# More examples: https://github.com/shillehbean/shillehtek-examples
#

-- Function to calculate factorial
function factorial(n)
    if n == 0 then
        return 1
    else
        return n * factorial(n - 1)
    end
end

-- Main code
local number = 5  -- You can change this number to calculate a different factorial
local result = factorial(number)
print("The factorial of " .. number .. " is " .. result)
