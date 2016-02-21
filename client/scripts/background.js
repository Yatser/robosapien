function str2ab(str) {
    var buf = new ArrayBuffer(str.length);
    var bufView = new Uint8Array(buf);
    for (var i = 0, strLen = str.length; i < strLen; i++) {
        bufView[i] = str.charCodeAt(i);
    }
    return buf;
}

var decoder = new TextDecoder('utf-8');
var port;
var socketId;

chrome.runtime.onConnect.addListener(function (new_port) {
    console.log('Port connected');
    port = new_port;
    port.onDisconnect.addListener(function() {
        console.log('Port disconnected');
        port = null;
    });
    port.onMessage.addListener(function (msg) {
        console.log(msg);
        if (socketId) {
            var arrayBuffer = str2ab(msg);
            chrome.sockets.tcp.send(socketId, arrayBuffer, function() {
                console.log('sent message');
            });
        }
    });
});

chrome.sockets.tcp.create({}, function (createInfo) {
    socketId = createInfo.socketId;
    chrome.sockets.tcp.connect(socketId, '172.16.1.76', 2000, function () {

        var fragment = '';

        chrome.sockets.tcp.onReceive.addListener(function (info) {
            if (info.socketId != socketId) {
                return;
            }

            fragment += decoder.decode(info.data);
            fragment = fragment.replace(/\r/g, '');
            while (fragment.indexOf('\n') >= 0) {
                var index = fragment.indexOf('\n');
                var message = fragment.slice(0, index);
                if (message && message.indexOf(':') >= 0) {
                    var split = message.split(':');
                    if (port) {
                        port.postMessage({key: split[0], value: split[1]});
                    }
                }
                fragment = fragment.slice(index + 1);
            }
        });
    });
});

chrome.app.runtime.onLaunched.addListener(function () {
    chrome.app.window.create('index.html', {
        'bounds': {
            'width': 1024,
            'height': 700
        }
    });
});