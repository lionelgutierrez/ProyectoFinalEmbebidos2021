import { Injectable } from '@angular/core';
import { environment } from '../../environments/environment';
import { HttpClient } from '@angular/common/http';
import {EstadsiticasSensores} from '../model/EstadsiticasSensores';

@Injectable({
  providedIn: 'root'
})
export class SensoresEstadisticasService {

  constructor(private _http:HttpClient) { 
  
  }

  getEstadisticasSensore(fecIni:string, fecFin:string) :Promise<EstadsiticasSensores[]>{
    //Estado = Curso / Cerrada
    let url =  environment.apiUrl+"/consultas/listadoSensoresFechas?fechaini="+fecIni+"&fechafin="+fecFin+"&nocache="+Date.now().toString();
    
    return this._http.get(url)
     .toPromise()
     .then((listado:EstadsiticasSensores[])=>{
         return listado;

    }).catch((err)=> {console.log("error en consulta a la API en getEstadisticasSensore");
                      var lista = [new EstadsiticasSensores(0,0,"")];
                      return lista;
    });    

  }

}
