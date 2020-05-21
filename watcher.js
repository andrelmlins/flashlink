var websocketReloader;
var LAST_SUCCESS_BUILD_STAMP =
  localStorage.getItem("LAST_SUCCESS_BUILD_STAMP") || 0;
var webSocketPort = 9999;

function setUpWebSocket() {
  if (websocketReloader == null || websocketReloader.readyState !== 1) {
    try {
      websocketReloader = new WebSocket(
        `ws://${window.location.hostname}:${webSocketPort}`
      );
      websocketReloader.onmessage = message => {
        var newData = JSON.parse(message.data).LAST_SUCCESS_BUILD_STAMP;
        if (newData > LAST_SUCCESS_BUILD_STAMP) {
          LAST_SUCCESS_BUILD_STAMP = newData;
          localStorage.setItem(
            "LAST_SUCCESS_BUILD_STAMP",
            LAST_SUCCESS_BUILD_STAMP
          );

          location.reload(true);
        }
      };
    } catch (exn) {
      console.error(
        "The watcher tried to connect to web socket, but failed. Here's the message:"
      );
      console.error(exn);
    }
  }
}

setUpWebSocket();
setInterval(setUpWebSocket, 2000);
