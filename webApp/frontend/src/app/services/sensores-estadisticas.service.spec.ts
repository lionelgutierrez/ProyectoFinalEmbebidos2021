import { TestBed } from '@angular/core/testing';

import { SensoresEstadisticasService } from './sensores-estadisticas.service';

describe('SensoresEstadisticasService', () => {
  let service: SensoresEstadisticasService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(SensoresEstadisticasService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
