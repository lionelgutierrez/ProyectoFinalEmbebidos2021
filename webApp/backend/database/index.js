var postgrespool = require('pg');
const configPool = new postgrespool.Pool({
    connectionLimit:10,
    host:'127.0.0.1',
    port: '5432',
    user: 'postgres',
    password: 'XXXXXX',
    database: 'ProyectoEmbebidos',
    max: 20,
    idleTimeoutMillis: 30000,
    connectionTimeoutMillis: 2000

});

configPool.connect((err, client, release) => {
    if (err) {
      return console.error('Error adquiriendo cliente', err.stack)
    }
    client.query('SELECT NOW()', (err, result) => {
      release()
      if (err) {
        return console.error('Error ejecutando query', err.stack)
      }
      console.log("Conexion a DB exitosa");
    })
  });

module.exports=configPool;
