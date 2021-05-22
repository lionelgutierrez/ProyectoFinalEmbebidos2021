import { TestBed } from '@angular/core/testing';

import { ElectrovalvEstadisticasService } from './electrovalv-estadisticas.service';

describe('ElectrovalvEstadisticasService', () => {
  let service: ElectrovalvEstadisticasService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(ElectrovalvEstadisticasService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
