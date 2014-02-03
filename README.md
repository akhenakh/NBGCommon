# NBGCommon

Useful debug tools for ios development.

NBGCommon is just macros for debugging, I used in every projects.

It uses the wonderful NSLogger to display your debug messages in a remote console but also log in the XCode debug console.
The code can be tweak to avoid NSLogger but give it a try you will never regret.

## Usage

Level is a number from 0 to 6 or more (see NSLogger documentation)
Tag is string (no need to @"")

* DLOGM(level, tag) Log Method name

* DLOG(level, tag, fmt, ...) Log format as NSLog

* DLOGV(level, tag, val) Log val any kind of NSObjects, structs, primitive data types

* DLOG_IMAGE(level, tag, imagedata, width, height) Will display the image in NSLogger
* DLOG_DATA(level, val, data) Will display the data in NSLogger

## Examples

### DLOGM
```objc
- (void)webSocket:(SRWebSocket *)webSocket didFailWithError:(NSError *)error {
    DLOGM(4, websocket);
}
``` 

Will display in the console:
```
2014-02-03 10:47:53.081 Tetrawords[55131:70b] <websocket> [NBNet.m:894 webSocket:didFailWithError:]
```

In NSLogger:
![alt tag](https://raw.github.com/akhenakh/NBGCommon/img/dlogm.png)

### DLOGV
```objc
- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    DLOGV(4, view, self.view.frame);
}
```

Will display in the console:
```
2014-02-03 10:50:16.319 Tetrawords[55919:70b] <view> [NBLoginViewController.m:71 viewWillAppear:] self.view.frame = {{0, 0}, {320, 568}}
```
In NSLogger:
![alt tag](https://raw.github.com/akhenakh/NBGCommon/img/dlogv.png)

### DLOG
```objc
DLOG(4, websocket,@"websocket closed with error: %@ reconnecting after %ds",
    [error localizedDescription], _websocketErrorCount * 2 );
```

Will display in the console:
```
2014-02-03 10:54:25.162 Tetrawords[56201:70b] <websocket> [NBNet.m:903 webSocket:didFailWithError:] websocket closed with error: The operation couldn’t be completed. Connection refused reconnecting after 8s
```
In NSLogger:
![alt tag](https://raw.github.com/akhenakh/NBGCommon/img/dlog.png)
