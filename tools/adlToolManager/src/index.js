// index






// Post requests
function SendData(command) {
    var request = new XMLHttpRequest();
    request.open('POST', '/', true);
    request.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded; charset=UTF-8');
    request.onload = function() {
        if (request.status >= 200 && request.status < 400) {
            Manager(this.responseText);
        }
    };

    request.send(command);
}    

function SendCommandData() {
    var request = new XMLHttpRequest();
    request.open('POST', '/', true);
    request.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded; charset=UTF-8');
    request.onload = function() {
        if (request.status >= 200 && request.status < 400) {
            Manager(this.responseText);
        }
    };
    var command = document.getElementById("command").value;

    request.send(command);
}

// Get request
function GetFile() {
    var request = new XMLHttpRequest();
    request.open('GET', '/', true);

    request.onload = function() {
    if (request.status >= 200 && request.status < 400) {
        document.getElementById("res").innerHTML = this.responseText;
    }
    };
    request.send();
}

// Replacer
function RootReplacer(key, value) {
    if (typeof(value) == "string") { // key == "path"
        value = value.replace(/\\/g, "/"); // Win "\" to "/" 
        value = value.replace(/..\/..\//g, ""); // Root to res file
    }
    if (key  == "name") {  
        value = value.replace(/\.[^/.]+$/g, "");
    }

    return value;
}

// Display functions
function TabManager(ManagerId) {
    var i, tabcontent, tablinks;
    tabcontent = document.getElementsByClassName("TabContent");
    for (i = 0; i < tabcontent.length; i++) {
        tabcontent[i].style.display = "none";
    }
    tablinks = document.getElementsByClassName("TabLink");
    for (i = 0; i < tablinks.length; i++) {
        tablinks[i].className = tablinks[i].className.replace(" active", "");
    }
    document.getElementById(ManagerId).style.display = "block";
}