const fs = require('fs');
const path = require('path');



FileCreator = function (classPath, options) {

    var className = path.basename(classPath);
    
    console.log("className: " + className);
    console.log("classPath: " + classPath);
    console.log("options: " + options);
    
    if (options != undefined) {
        settings = options.split(",");  
    }

    console.log("settings: " + settings);

    
    var cppFile = '#include "'+ className + '.h"\n\n'
                    + ((settings[1] == 'true')?'#include "engine/adl_entities/adlEntity_factory.h"\n\n': '')
                    + className + '::' + className + '()\n'
                    + '{\n'
                    + ((settings[1] == 'true')?'\tREGISTER_ACTOR(' + className + ')\n': '\n')
                    + '}\n\n'
                    + className + '::~' + className + '()\n'
                    + '{\n\n}\n\n'
                    + ((settings[0] == 'isEntity')?'void ' + className + '::init() {\n\n}\n\n' : '')
                    + ((settings[0] == 'isEntity')?'void ' + className + '::update(float dt) {\n\n}\n\n' : '')
                    + ((settings[2] == 'true')?'void ' + className + '::deserialize(const rapidjson::Value& json_object)\n{\n\n}\n\n': '')
    
    var hFile = '#ifndef ' + className + '_h__\n' 
                + '#define ' + className + '_h__\n\n'
                + ((settings[3] != '')?'#include "engine/adl_entities/' + settings[3] + '.h"\n\n': '')
                + ((settings[3] != '')?'class ' + className + ' : public ' + settings[3] + ' { \n\n': 'class ' + className + ' { \n\n')
                + 'public:\n\n'
                + '\t' + className +'();\n'
                + '\t~' + className + '();\n\n'
                + ((settings[0] == 'isEntity')?'\tvoid init() override;\n' : '')
                + ((settings[0] == 'isEntity')?'\tvoid update(float dt) override;\n\n' : '')
                + ((settings[2] == 'true')?'\tvoid deserialize(const rapidjson::Value& json_object) override;\n\n': '')
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