const fs = require('fs');
const path = require('path');



FileCreator = function (classPath) {

    var className = path.basename(classPath);
    
    console.log("className: " + className);
    console.log("classPath: " + classPath);
    

    var cppFile = '#include "'+ className + '.h"\n\n'
                    + className + '::' + className + '()\n'
                    + '{\n\n}\n\n'
                    + className + '::~' + className + '()\n'
                    + '{\n\n}\n\n'
                    + 'void ' + className + '::init()'
                    + '{\n\n}\n\n'
                    + 'void ' + className + '::update(float dt)'
                    + '{\n\n}\n'
                    + '\n';
                    //+ 'void ' + className + '::deserialize(const rapidjson::Value& json_object)'
                    //+ '{\n\n}\n\n';
    var hFile = '#ifndef ' + className + '_h__\n' 
                + '#define ' + className + '_h__\n\n'
                + 'class ' + className + ' { \n\n'
                + 'public:\n\n'
                + '\t' + className +'();\n'
                + '\t~' + className + '();\n\n'
                + '\tvoid init() override;\n'
                + '\tvoid update(float dt) override;\n'
                //+ 'void deserialize(const rapidjson::Value& json_object) override;\n'
                + '\n'
                + 'private:\n\n'
                + '};\n\n'
                + '#endif //' + className + '_h__\n';

    fs.writeFileSync(classPath + '.cpp', cppFile);
    fs.writeFileSync(classPath + '.h', hFile);

    var clssFiles = {cpp: cppFile, h: hFile} 

    return clssFiles;
}

module.exports = {
    FileCreator: FileCreator
};