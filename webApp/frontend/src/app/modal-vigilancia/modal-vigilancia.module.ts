import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';

import { IonicModule } from '@ionic/angular';

import { ModalVigilanciaPageRoutingModule } from './modal-vigilancia-routing.module';

import { ModalVigilanciaPage } from './modal-vigilancia.page';

@NgModule({
  imports: [
    CommonModule,
    FormsModule,
    IonicModule,
    ModalVigilanciaPageRoutingModule
  ],
  declarations: [ModalVigilanciaPage]
})
export class ModalVigilanciaPageModule {}
