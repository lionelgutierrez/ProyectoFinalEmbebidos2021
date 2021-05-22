var express = require("express");
var recepcionNucleo = express.Router();
var modelo = require('../../DAL');

recepcionNucleo.get("/",async function(req,res){
    
    var accion = null;
    estado = req.query.accion;
    if (estado == undefined)
    {
        res.send("Falta informacion de  accion");
        return;
    }
    
    if ((estado == "ON") || (estado == "OFF"))
    {
        modelo.registrarDatoElectrovalvula(estado);
        res.send("OK");
        req.io.emit('electrovalvula',{estado: estado});
    }
    else 
    {
        res.send("Accion incorrecta");
        return;
    }

});


module.exports =recepcionNucleo;