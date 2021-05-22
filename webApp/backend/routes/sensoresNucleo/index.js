var express = require("express");
var sensoreNucleo = express.Router();
var modelo = require('../../DAL');

sensoreNucleo.get("/",async function(req,res){
    
    var temperatura = null;
    var humedad = null;
    temperatura = req.query.temp;
    humedad  = req.query.hum
    if (temperatura == undefined)
    {
        res.send("Falta informacion de temperatura");
        return;
    }

    if (humedad == undefined)
    {
        res.send("Falta infomracion de humedad");
        return;
    }    

    modelo.registrarDatosSensores(temperatura,humedad);
    res.send("OK");
    req.io.emit('sensores',{temperatura: temperatura, humedad: humedad});

});

module.exports =sensoreNucleo;