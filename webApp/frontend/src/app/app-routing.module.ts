import { NgModule } from '@angular/core';
import { PreloadAllModules, RouterModule, Routes } from '@angular/router';

const routes: Routes = [
  {
    path: '',
    redirectTo: 'sensores',
    pathMatch: 'full'
  },
  {
    path: 'sensores',
    loadChildren: () => import('./sensores/sensores.module').then( m => m.SensoresPageModule)
  },
  {
    path: 'electrovalvula',
    loadChildren: () => import('./electrovalvula/electrovalvula.module').then( m => m.ElectrovalvulaPageModule)
  }
];

@NgModule({
  imports: [
    RouterModule.forRoot(routes, { preloadingStrategy: PreloadAllModules })
  ],
  exports: [RouterModule]
})
export class AppRoutingModule {}
