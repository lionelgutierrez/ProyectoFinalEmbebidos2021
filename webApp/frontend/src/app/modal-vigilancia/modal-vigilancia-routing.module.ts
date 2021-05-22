import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { ModalVigilanciaPage } from './modal-vigilancia.page';

const routes: Routes = [
  {
    path: '',
    component: ModalVigilanciaPage
  }
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule],
})
export class ModalVigilanciaPageRoutingModule {}
