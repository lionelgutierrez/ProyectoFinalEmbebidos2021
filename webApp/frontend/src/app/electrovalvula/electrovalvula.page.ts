import { Component, OnInit } from '@angular/core';
import { ChartDataSets, ChartOptions,ChartType } from 'chart.js';
import { Color, Label, MultiDataSet,SingleDataSet,monkeyPatchChartJsLegend,monkeyPatchChartJsTooltip } from 'ng2-charts';
import { DatePipe, getLocaleDayPeriods } from '@angular/common';
import {MatDatepicker,MatDatepickerToggle} from '@angular/material/datepicker';
import {MatIcon} from '@angular/material/icon';
import {FormControl} from '@angular/forms';
import {EstadisticasElectrovalvula} from '../model/EstadisticasElectrovalvula';
import {ElectrovalvEstadisticasService} from '../services/electrovalv-estadisticas.service';
import { ModalController } from '@ionic/angular';
import {ModalVigilanciaPage} from '../modal-vigilancia/modal-vigilancia.page'
import { SocketService } from '../services/socket.service';
import {Observable, Subscription} from 'rxjs';

import { NativeDateAdapter, DateAdapter,
  MAT_DATE_FORMATS, 
  MAT_DATE_LOCALE} from '@angular/material/core';
import { formatDate } from '@angular/common';

export const PICK_FORMATS = {
  parse: {dateInput: {month: 'numeric', year: 'numeric', day: 'numeric'}},
  display: {
      dateInput: 'input',
      monthYearLabel: {year: 'numeric', month: 'short'},
      dateA11yLabel: {year: 'numeric', month: 'numeric', day: 'numeric'},
      monthYearA11yLabel: {year: 'numeric', month: 'numeric'}
  }
};

class PickDateAdapter extends NativeDateAdapter {
  format(date: Date, displayFormat: Object): string {
      if (displayFormat === 'input') {
          return formatDate(date,'dd/MM/yyyy',this.locale);
      } else {
           return formatDate(date,'EEEE, dd MMMM yyyy',this.locale);//date.toDateString();
      }
  }
}

@Component({
  selector: 'app-electrovalvula',
  templateUrl: './electrovalvula.page.html',
  styleUrls: ['./electrovalvula.page.scss'],
  providers: [
    {provide: DateAdapter, useClass: PickDateAdapter},
    {provide: MAT_DATE_FORMATS, useValue: PICK_FORMATS}]    
})
export class ElectrovalvulaPage implements OnInit {

  public fecIni:string = this.datePipe.transform(Date.now(),"dd/MM/yyyy");
  public fecFin:string = this.datePipe.transform(Date.now(),"dd/MM/yyyy");
  public fechaDateIni:Date
  public fechaDateFin:Date;
  public listadoDatos: EstadisticasElectrovalvula[] = [];
  miObservableSocket: Observable<any>;
  suscripcion: Subscription = null;
  modalAviso = null;

  lineChartOptions: ChartOptions = {
    responsive: true,
  };
  lineChartLabels: Label[] = [];
  lineChartType: ChartType = 'line';
  lineChartLegend = true;
  lineChartPlugins = [];

  lineChartData: ChartDataSets[] = [
    { data: [], label: 'Estado (0=OFF, 1=ON)' }
    
  ];

  constructor(private datePipe:DatePipe,
              private electrovalvEstadisticasService:ElectrovalvEstadisticasService,
              public modalController: ModalController,
              private socketService:SocketService
              ) { 
    monkeyPatchChartJsTooltip();
    monkeyPatchChartJsLegend();

  }

  cargarValoresGrafico() {

    this.lineChartLabels = [];
    this.lineChartData[0].data = [];
    let datosElectrovalvula = [];
    
    if (this.fechaDateIni == null) {
       alert("Falta especificar la fecha de inicio o el formato no es correcto. Seleccione fecha");
       return;
    }
    if (this.fechaDateFin == null) {
       alert("Falta especificar la fecha de fin o el formato no es correcto. Seleccione fecha");
       return;
    }

   this.fecIni = this.datePipe.transform(this.fechaDateIni,"dd/MM/yyyy");
   this.fecFin = this.datePipe.transform(this.fechaDateFin,"dd/MM/yyyy");
    
    //Inovoco servico para obtener los datos y cargo los valores
    this.electrovalvEstadisticasService.getEstadisticasElectov(this.fecIni,this.fecFin
                                                  ).then((listado)=>{
                                                    this.listadoDatos = listado;
                                                    let longitud :number= listado.length;
                                                    for (let idx = 0; idx < longitud; idx++) {
                                                      this.lineChartLabels.push(listado[idx].fecha);  
                                                      if (listado[idx].estado == "ON") {
                                                         datosElectrovalvula[idx] = 1;
                                                      }
                                                      else {
                                                        datosElectrovalvula[idx] = 0;
                                                      }                                                      
                                                    }

                                                    this.lineChartData[0].data= datosElectrovalvula;
                                                    
                                                    

    });

  }

  ngOnInit() {
    this.connectSocket();
  }

  async createModal(mensaje:string,mensaje2:string,pagina:string) {
    const modal = await this.modalController.create({
      component: ModalVigilanciaPage,
      componentProps: { mensaje: mensaje,mensaje2:mensaje2,pagina:pagina}
    });

    await modal.present();
    this.modalAviso = modal;
    
  }

  connectSocket() {
    this.miObservableSocket = this.socketService.listen("electrovalvula");
    this.suscripcion = this.miObservableSocket.subscribe(res=> {
        let mensaje = "La electrovalvula se apagó";
        if (res.estado == "ON") {
          mensaje = "La electrovalvula se activó"
        }
        let mensaje2 = "Estado electrovalvula: "+res.estado;
        this.createModal(mensaje,mensaje2,"electrovalvula");
        setTimeout(()=>{
          this.dismissModal();
          this.cargarValoresGrafico();
        }, 6000);
    });
  }  

  dismissModal() {
    if (this.modalAviso) {
      this.modalAviso.dismiss().then(() => { this.modalAviso = null; });
    }
  }

}
