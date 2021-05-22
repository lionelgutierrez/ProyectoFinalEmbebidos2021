import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { IonicModule } from '@ionic/angular';
import { SensoresPageRoutingModule } from './sensores-routing.module';
import { SensoresPage } from './sensores.page';
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
    SensoresPageRoutingModule,
    ChartsModule,
    MatDatepickerModule,
    MatInputModule,
    MatIconModule ,
    ModalVigilanciaPageModule       
  ],
  declarations: [SensoresPage]
})
export class SensoresPageModule {}
