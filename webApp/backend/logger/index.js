fs = require('fs');
var os = require("os");
var fcionesEstandar = require('../funcionesEstandar');

async function registrarLogError(texto) {
    var entrada = fcionesEstandar.ahoraString() + "->" + texto;
    var archivo = "./logs/log-"+ fcionesEstandar.hoyString()+".txt";
    fs.appendFile(archivo, entrada + os.EOL, function (err) {
        if (err) return console.log("Error en logging de entrada. "+archivo+ ". Datos: "+entrada);
      });

}

module.exports = {registrarLogError}