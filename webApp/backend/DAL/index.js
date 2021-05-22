var pool = require('../database');
var logger = require("../logger");

async function registrarDatosSensores(temp,humedad) {
  var consulta = 'INSERT INTO public."SENSORES_DATOS" ("TEMPERATURA", "HUMEDAD", "FECHA")';
  consulta += ' VALUES ($1,$2,NOW()) ';
  var parametros = [temp,humedad];

  try {
      var res = await pool.query(consulta,parametros)
      return res.rowCount;
  } 
  catch(err) {
      logger.registrarLogError("DAL.registrarDatosSensores.error: "+err);
      return undefined;
  }  
}

async function registrarDatoElectrovalvula(estado) {
  var consulta = 'INSERT INTO public."electrovalvula_datos" ("ESTADO", "FECHA")';
  consulta += ' VALUES ($1,NOW()) ';
  var parametros = [estado];

  try {
      var res = await pool.query(consulta,parametros)
      return res.rowCount;
  } 
  catch(err) {
      logger.registrarLogError("DAL.registrarDatoElectrovalvula.error: "+err);
      return undefined;
  }  
}


async function listadoEventosElectovalvFechas(fechaIni,fechaFin){

  var consulta = 'SELECT "ESTADO" as estado,TO_CHAR("FECHA",\'DD/MM/YYYY HH24:MI:SS\') AS FECHA';
  consulta +=' FROM public."electrovalvula_datos" AS E ';
  consulta +=' WHERE E."FECHA" >= $1 ';
  consulta +=' and E."FECHA" <= $2 ';
  consulta +=' ORDER BY "FECHA" ASC  ';
  
  try {
      var res = await pool.query(consulta,[fechaIni,fechaFin])
      return res.rows;
    } 
  catch (err) {
      logger.registrarLogError("DAL.listadoEventosElectovalvFechas.error: "+err)
      return undefined;
  }  

}

async function listadoSensoresFechas(fechaIni,fechaFin){

  var consulta = 'SELECT "TEMPERATURA" as temperatura,"HUMEDAD" as humedad,TO_CHAR("FECHA",\'DD/MM/YYYY HH24:MI:SS\') AS FECHA';
  consulta +=' FROM public."SENSORES_DATOS" AS S ';
  consulta +=' WHERE S."FECHA" >= $1 ';
  consulta +=' and S."FECHA" <= $2 ';
  consulta +=' ORDER BY "FECHA" ASC  ';
  
  try {
      var res = await pool.query(consulta,[fechaIni,fechaFin])
      return res.rows;
    } 
  catch (err) {
      logger.registrarLogError("DAL.listadoSensoresFechas.error: "+err)
      return undefined;
  }  

}

module.exports={registrarDatosSensores,registrarDatoElectrovalvula,
                listadoEventosElectovalvFechas,listadoSensoresFechas
               }