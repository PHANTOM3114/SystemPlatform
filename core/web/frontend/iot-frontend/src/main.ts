import { bootstrapApplication } from '@angular/platform-browser';
import { appConfig } from './app/app.config';
import { AppComponent } from './app/app.component';
import { HttpClientModule } from '@angular/common/http';
import { importProvidersFrom } from '@angular/core';

// bootstrapApplication(AppComponent, appConfig)
//   .catch((err) => console.error(err));

bootstrapApplication(AppComponent, {  // <---- ПОЧАТОК ОБ'ЄКТА З `providers: [...]`, СУКА!
  providers: [ // <---- МАСИВ `providers: [...]`, СУКА!
    importProvidersFrom(HttpClientModule) // <---- ПРОВАЙДЕР `HttpClientModule`, СУКА!
  ]
}) // <---- ЗАКІНЧЕННЯ ОБ'ЄКТА, СУКА!
