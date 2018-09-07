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
        info.children = fs.readdirSync(filename).map(function(child) {
            return TreeBuilder(filename + '/' + child);
        });
    } else {
        //info.type = "file";
    }

    return info;
}


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
    TreeBuilder: TreeBuilder
};