// Node-RED function node that responds to a Telegram "status" command by reading latest temperature and pressure from flow context and sending a formatted message back to the chat.
//
// Full tutorial: https://shillehtek.com/blogs/news/node-red-telegram-sensor-status
// Parts used: https://shillehtek.com/products/shillehtek-bmp180-pre-soldered
// More examples: https://github.com/shillehbean/shillehtek-examples
//

let cmd = msg.payload.content.toLowerCase();

if (cmd === "status") {
    let temp = flow.get("latestTemp") || "N/A";
    let pressure = flow.get("latestPressure") || "N/A";

    msg.payload = {
        chatId: msg.payload.chatId,
        type: "message",
        content: `🌡️ Temp: ${temp} °C\n🌬️ Pressure: ${pressure} hPa`
    };
    return msg;
}

return null;
