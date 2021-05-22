var express = require("express");
var bodyParser = require("body-parser");
var app = express();
var PORT = 4000;
var cors = require('cors');

var corsConfig={
    origin:'*',
    optionsSucessStatus:200
};

app.use(cors(corsConfig));

//Configuro conexion de socket
var http = require('http');
var server = http.createServer(app);
var io = require('socket.io')(server, {
  cors: {
    origin: '*',
  }
});

app.use(function(req, res, next) {
  req.io = io;
  next();
});
io.on('connection', function(socket) {
  console.log('conexion a socket');
});


// parsea requests con content-type - application/json
app.use(bodyParser.json());
// parsea requests con content-type - application/x-www-form-urlencoded
app.use(bodyParser.urlencoded({ extended: true }));

var routerNucleo= require("./routes/recepcionNucleo");
var sensoreNucleo= require("./routes/sensoresNucleo");
var consultas= require("./routes/consultas");

app.use(express.json());
//Ruta para recepcion de datos de electrovalvula de la nucleo
app.use("/accion",routerNucleo);
//Ruta para recepcion de datos de sensores de humjedad y temperatura de la nucleo
app.use("/sensores",sensoreNucleo);
//Ruta para consulta de datos
app.use("/consultas",consultas);

server.listen(PORT,function(req,res){
  console.log("App levantada");
})

