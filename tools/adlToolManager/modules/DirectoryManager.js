const fs = require('fs');
const path = require('path');

TreeBuilder = function (filename) {
    var stats = fs.lstatSync(filename),
        info = {
            name: path.basename(filename),
            path: filename
        };

    if (stats.isDirectory()) {
        //info.type = "folder";
        info.children = fs.readdirSync(filename).map(function (child) {
            return TreeBuilder(filename + '/' + child);
        });
    } else {
        //info.type = "file";
    }

    return info;
}

CountLines = function (filePath, callback) {
    let i;
    let count = 0;
    fs.createReadStream(filePath)
        .on('error', e => callback(e))
        .on('data', chunk => {
            for (i = 0; i < chunk.length; ++i) if (chunk[i] == 10) count++; // new line
        })
        .on('end', () => callback(count));
};

CountLinesSync = function (filePath, ) {
    var index = 0;
    var count = 0;

    chunk =  fs.readFileSync(filePath).toString();
    count = chunk.split("\n").length;

    //console.log(filePath + " : " + count + " : \n" + chunk);
    
    return count;
};


module.exports = {
    walkSync: function (dir, filelist = []) {
        fs.readdirSync(dir).forEach(file => {
            const dirFile = path.join(dir, file);
            try {
                filelist = this.walkSync(dirFile, filelist);
            }
            catch (err) {
                if (err.code === 'ENOTDIR' || err.code === 'EBUSY') filelist = [...filelist, dirFile];
                else throw err;
            }
        });
        return filelist;
    },
    TreeBuilder: TreeBuilder,
    CountLines: CountLines,
    CountLinesSync: CountLinesSync
};