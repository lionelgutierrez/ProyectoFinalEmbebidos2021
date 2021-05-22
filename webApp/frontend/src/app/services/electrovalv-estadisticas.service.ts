import { Injectable } from '@angular/core';
import { environment } from '../../environments/environment';
import { HttpClient } from '@angular/common/http';
import {EstadisticasElectrovalvula} from '../model/EstadisticasElectrovalvula';

@Injectable({
  providedIn: 'root'
})
export class ElectrovalvEstadisticasService {

  constructor(private _http:HttpClient) { 
  
  }

  getEstadisticasElectov(fecIni:string, fecFin:string) :Promise<EstadisticasElectrovalvula[]>{
    //Estado = Curso / Cerrada
    let url =  environment.apiUrl+"/consultas/listadoEventosElectovalvFechas?fechaini="+fecIni+"&fechafin="+fecFin+"&nocache="+Date.now().toString();
    
    return this._http.get(url)
     .toPromise()
     .then((listado:EstadisticasElectrovalvula[])=>{
         return listado;

    }).catch((err)=> {console.log("error en consulta a la API en getEstadisticasElectov");
                      var lista = [new EstadisticasElectrovalvula("","")];
                      return lista;
    });    

  }

}
