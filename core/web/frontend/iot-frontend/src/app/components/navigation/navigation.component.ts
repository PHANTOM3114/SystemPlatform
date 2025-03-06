import { Component } from '@angular/core';
import { Router, RouterModule } from '@angular/router';
import { Menubar } from 'primeng/menubar';
import { MenubarModule } from 'primeng/menubar';
import { MenuItem } from 'primeng/api';


@Component({
  selector: 'app-navigation',
  standalone: true,
  imports: [Menubar, RouterModule],
  // templateUrl: './navigation.component.html',
  // styleUrl: './navigation.component.css'
  template: `
    <p-menubar [model]="items"></p-menubar>
  `,
  styles: [`
  p-menubar {
      background: #333;
      color: white;
      border: none;
    }
    ::ng-deep .p-menubar-root-list {
      display: flex;
      gap: 10px;
    }
  `]
})
export class NavigationComponent {
  items: MenuItem[];

  constructor() {
    this.items = [
      { label: 'Home', icon: 'pi pi-home', routerLink: '/' },
      { label: 'Devices', icon: 'pi pi-tablet', routerLink: '/devices' },
      { label: 'Analytics', icon: 'pi pi-chart-bar', routerLink: '/analytics' },
      { label: 'Settings', icon: 'pi pi-cog', routerLink: '/settings' }
    ];
  }
}