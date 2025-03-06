import { Routes } from '@angular/router';
import { HomeComponent } from './components/navigation/home/home.component';
import { DevicesComponent } from './components/navigation/devices/devices.component';
import { AnalyticsComponent } from './components/navigation/analytics/analytics.component';
import { SettingsComponent } from './components/navigation/settings/settings.component';

// export const routes: Routes = [
//     { path: '', loadComponent: () => import('./components/navigation/home/home.component').then(m => m.HomeComponent) },
//     { path: 'devices', loadComponent: () => import('./components/navigation/devices/devices.component').then(m => m.DevicesComponent) },
//     { path: 'analytics', loadComponent: () => import('./components/navigation/analytics/analytics.component').then(m => m.AnalyticsComponent) },
//     { path: 'settings', loadComponent: () => import('./components/navigation/settings/settings.component').then(m => m.SettingsComponent) }
// ];

export const routes: Routes = [
  { path: 'home', component: HomeComponent },
  { path: 'devices', component: DevicesComponent },
  { path: 'analytics', component: AnalyticsComponent },
  { path: 'settings', component: SettingsComponent },
  { path: '', redirectTo: '/home', pathMatch: 'full' } // редірект на домашню сторінку
];