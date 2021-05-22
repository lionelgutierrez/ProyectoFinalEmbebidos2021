import { Component, OnInit } from '@angular/core';
import { NavParams } from '@ionic/angular';

@Component({
  selector: 'app-modal-vigilancia',
  templateUrl: './modal-vigilancia.page.html',
  styleUrls: ['./modal-vigilancia.page.scss'],
})
export class ModalVigilanciaPage implements OnInit {
  mensaje: string;
  mensaje2: string;
  pagina:string;
  constructor(navParams: NavParams) { 

    this.mensaje=navParams.get('mensaje');
    this.mensaje2=navParams.get('mensaje2');
    this.pagina=navParams.get('pagina');
  }

  ngOnInit() {
  }

}
