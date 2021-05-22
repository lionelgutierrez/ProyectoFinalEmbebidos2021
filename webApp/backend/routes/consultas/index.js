var express = require("express");
var consultas = express.Router();
var modelo = require('../../DAL');
var logger = require("../../logger");

consultas.get("/listadoEventosElectovalvFechas", async function(req,res){
    
    try {
        valor = await modelo.listadoEventosElectovalvFechas(req.query.fechaini,req.query.fechafin);
        res.send(valor);
     }
     catch (error) {
         await logger.registrarLogError("Error en listadoEventosElectovalvFechas con fecha inicio: "+req.params.fechaini+" ,fecha fin:"+req.query.fechafin+" : "+error);
         res.send({});
     }    
   
});

consultas.get("/listadoSensoresFechas", async function(req,res){
    
    try {
        valor = await modelo.listadoSensoresFechas(req.query.fechaini,req.query.fechafin);
        res.send(valor);
     }
     catch (error) {
         await logger.registrarLogError("Error en listadoSensoresFechas con fecha inicio: "+req.params.fechaini+" ,fecha fin:"+req.query.fechafin+" : "+error);
         res.send({});
     }    
   
});

module.exports =consultas;