var http = require('http');
var fs = require('fs');
var path = require('path');
var mm = require('./ModuleManager');

var server = http.createServer(function (request, response) {
    console.log('request ', request.url);

    // POST
    if (request.method == 'POST') {
        console.log("POST");
        var body = '';

        request.on('data', function (data) {
            body += data;
            // console.log("Partial body: " + body);
        });

        request.on('end', function () {
            // console.log("Body: " + body);
            // console.log("Splitted Body: " + body.split(":"));
            
            var outputs = {};
            outputs.res = mm.PostManager(body);
            outputs.command = body.split(":")[0];
            
            // console.log("outputs:");
            // console.log(JSON.stringify(outputs, null, 2));
            
            response.writeHead(200, {'Content-Type': 'application/json'});
            response.end(JSON.stringify(outputs));
        });

        return;
    }

    // GET 
    var filePath = '.' + request.url;
    if (filePath == './') {
        filePath = './index.html';
    }

    var extname = String(path.extname(filePath)).toLowerCase();
    var mimeTypes = {
        '.html': 'text/html',
        '.js': 'text/javascript',
        '.css': 'text/css',
        '.json': 'application/json',
        '.png': 'image/png',
        '.jpg': 'image/jpg',
        '.gif': 'image/gif',
        '.wav': 'audio/wav',
        '.mp4': 'video/mp4',
        '.woff': 'application/font-woff',
        '.ttf': 'application/font-ttf',
        '.eot': 'application/vnd.ms-fontobject',
        '.otf': 'application/font-otf',
        '.svg': 'application/image/svg+xml'
    };

    var contentType = mimeTypes[extname] || 'application/octet-stream';

    fs.readFile(filePath, function(error, content) {
        if (error) {
            if(error.code == 'ENOENT') {
                fs.readFile('./404.html', function(error, content) {
                    response.writeHead(200, { 'Content-Type': contentType });
                    response.end(content, 'utf-8');
                });
            }
            else {
                response.writeHead(500);
                response.end('Sorry, check with the site admin for error: '+error.code+' ..\n');
                response.end();
            }
        }
        else {
            response.writeHead(200, { 'Content-Type': contentType });
            response.end(content, 'utf-8');
        }
    });
    
}).listen(8520);
console.log('Server running at http://127.0.0.1:8520/');