function ahoraString() {
    var fecAhora = new Date();
    var fechaStr =
            ("00" + fecAhora.getDate()).slice(-2) + "/" +
            ("00" + (fecAhora.getMonth() + 1)).slice(-2) + "/" +
            fecAhora.getFullYear() + " " +
            ("00" + fecAhora.getHours()).slice(-2) + ":" +
            ("00" + fecAhora.getMinutes()).slice(-2) + ":" +
            ("00" + fecAhora.getSeconds()).slice(-2);
    return  fechaStr;       

}

function hoyString() {
    var fecAhora = new Date();
    var fechaStr =
            ("00" + fecAhora.getDate()).slice(-2) + "-" +
            ("00" + (fecAhora.getMonth() + 1)).slice(-2) + "-" +
            fecAhora.getFullYear();
    return fechaStr;       

}

module.exports={ahoraString,hoyString}