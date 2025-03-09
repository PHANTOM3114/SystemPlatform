import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';
import { MenubarModule } from 'primeng/menubar';
import { MenuItem } from 'primeng/api';

@Component({
  selector: 'app-navigation',
  standalone: true,
  imports: [CommonModule, MenubarModule],
  template: `
    <p-menubar [model]="items"></p-menubar>
  `,
  styles: [],
})
export class NavigationComponent {
  items: MenuItem[] | undefined;

  constructor() {
    this.items = [
      {
        label: 'Файли',
        icon: 'pi pi-fw pi-file',
        items: [
          {
            label: 'Новий',
            icon: 'pi pi-fw pi-plus',
            items: [
              {
                label: 'Проєкт',
                icon: 'pi pi-fw pi-folder-open',
              },
              {
                label: 'Файл',
                icon: 'pi pi-fw pi-file',
              },
            ],
          },
          {
            label: 'Відкрити',
            icon: 'pi pi-fw pi-folder-open',
          },
          {
            separator: true,
          },
          {
            label: 'Вийти',
            icon: 'pi pi-fw pi-times',
          },
        ],
      },
      {
        label: 'Редагувати',
        icon: 'pi pi-fw pi-pencil',
        items: [
          {
            label: 'Видалити',
            icon: 'pi pi-fw pi-trash',
          },
          {
            label: 'Оновити',
            icon: 'pi pi-fw pi-refresh',
          },
        ],
      },
      {
        label: 'Користувачі',
        icon: 'pi pi-fw pi-user',
        items: [
          {
            label: 'Новий',
            icon: 'pi pi-fw pi-user-plus',
          },
          {
            label: 'Видалити',
            icon: 'pi pi-fw pi-user-minus',
          },
          {
            label: 'Пошук',
            icon: 'pi pi-fw pi-users',
            items: [
              {
                label: 'Фільтр',
                icon: 'pi pi-fw pi-filter',
              },
              {
                icon: 'pi pi-fw pi-bars',
                label: 'Список',
              },
            ],
          },
        ],
      },
      {
        label: 'Події',
        icon: 'pi pi-fw pi-calendar',
        items: [
          {
            label: 'Редагувати',
            icon: 'pi pi-fw pi-pencil',
            items: [
              {
                label: 'Зберегти',
                icon: 'pi pi-fw pi-calendar-plus',
              },
              {
                label: 'Видалити',
                icon: 'pi pi-fw pi-calendar-minus',
              },
            ],
          },
          {
            label: 'Архів',
            icon: 'pi pi-fw pi-calendar-times',
            items: [
              {
                label: 'Завантажити',
                icon: 'pi pi-fw pi-arrow-down',
              },
            ],
          },
        ],
      },
      {
        label: 'Вийти',
        icon: 'pi pi-fw pi-power-off',
      },
    ];
  }
}