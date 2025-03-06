import { bootstrapApplication } from '@angular/platform-browser';
import { appConfig } from './app/app.config';
import { AppComponent } from './app/app.component';
import { HttpClientModule } from '@angular/common/http';
import { importProvidersFrom } from '@angular/core';
import { provideRouter, Routes } from '@angular/router';

// PrimeNG imports
import { MenubarModule } from 'primeng/menubar';
import { routes } from './app/app.routes';

// bootstrapApplication(AppComponent, appConfig)
//   .catch((err) => console.error(err));

bootstrapApplication(AppComponent, {  // <---- ПОЧАТОК ОБ'ЄКТА З `providers: [...]`, СУКА!
  providers: [ // <---- МАСИВ `providers: [...]`, СУКА!
    importProvidersFrom(HttpClientModule), // <---- ПРОВАЙДЕР `HttpClientModule`, СУКА!
    importProvidersFrom([ // <---- Додай масив `importProvidersFrom([...])` з модулями PrimeNG, блять!
      MenubarModule,
      // ... і так далі, додай імпортовані модулі сюди ...
    ]),
    provideRouter(routes),
  ]
}) // <---- ЗАКІНЧЕННЯ ОБ'ЄКТА, СУКА!

