import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { IonicModule } from '@ionic/angular';
import { ElectrovalvulaPageRoutingModule } from './electrovalvula-routing.module';
import { ElectrovalvulaPage } from './electrovalvula.page';
import { ChartsModule } from 'ng2-charts';
import {MatDatepickerModule} from '@angular/material/datepicker';
import {MatInputModule} from '@angular/material/input';
import {MatIconModule} from '@angular/material/icon';
import {DateAdapter,MAT_DATE_LOCALE,NativeDateAdapter} from '@angular/material/core';
import {ModalVigilanciaPageModule} from '../modal-vigilancia/modal-vigilancia.module'

@NgModule({
  imports: [
    CommonModule,
    FormsModule,
    IonicModule,
    ElectrovalvulaPageRoutingModule,
    ChartsModule,
    MatDatepickerModule,
    MatInputModule,
    MatIconModule,
    ModalVigilanciaPageModule      
  ],
  declarations: [ElectrovalvulaPage]
})
export class ElectrovalvulaPageModule {}
