#include "xpadtest.h"
#include "ncursesVersion1.h"

int main()
{
	WINDOW *menu_win;
	WINDOW *second_menu;
	WINDOW *led_menu;
	
	int highlight = 1;
	int ledhighlight = 1;
	int choice = 0;
	int ledchoice = 0;
	int c;
	int l;
	bool led_menu_selected = false;
	//if(run()==1){printf("Fail\n");}
	libusb_init(NULL);

	h = libusb_open_device_with_vid_pid(NULL, vid, pid);
	libusb_set_auto_detach_kernel_driver(h,0);
	libusb_claim_interface(h, 0);
	initscr();
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
	startx = 10;
	starty = (24 - HEIGHT) / 2;
	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	second_menu = newwin(HEIGHT, (WIDTH*2), (starty),(startx*4));
	led_menu = newwin(HEIGHT, (WIDTH*2), (starty),(startx*4));
	keypad(menu_win, TRUE);
	refresh();
	print_menu(menu_win, highlight);
	print_second_menu(second_menu,highlight);
	scrollok(second_menu,TRUE);
	while(1)
	{	
		if(led_menu_selected == false)
		{
			c = wgetch(menu_win);
			switch(c)
			{	case KEY_UP:
					if(highlight == 1)
						highlight = n_choices;
					else
						--highlight;
					break;
				case KEY_DOWN:
					if(highlight == n_choices)
						highlight = 1;
					else 
						++highlight;
					break;
				case 10:
					choice = highlight;
					break;
			}
		
			if(c==10){printInSecondMenu(second_menu,choice);}
			if(c==10 && choice==1){
				while(strcmp(check(),"Back              ")!=0)
					{
						mvwprintw(second_menu, secondY, secondX, "Button pressed : %s",check());
						printInSecondMenu(second_menu,choice);
						refresh();
						print_second_menu(second_menu,1);

					}
				}
			if(c == 10 && choice == 2 ){led_menu_selected=true;keypad(menu_win,FALSE);keypad(led_menu,TRUE);leds_menu(led_menu,ledhighlight);refresh();}
			if(c == 10 && choice == 3 ){doRumble(choices[3]);}
			if(c == 10 && choice == 4 ){doRumble(choices[4]);}
			if(c == 10 && choice == 5){break;}
		}
			
			
		if(led_menu_selected == true)
		{
				l = wgetch(led_menu);
				switch(l)
				{	case KEY_UP:
						if(ledhighlight == 1)
							ledhighlight = l_choices;
						else
							--ledhighlight;
						break;
					case KEY_DOWN:
						if(ledhighlight == l_choices)
							ledhighlight = 1;
						else 
							++ledhighlight;
						break;
					case 10:
						ledchoice = ledhighlight;
						break;
				}
				leds_menu(led_menu,ledhighlight);
				if (l == 10 && ledchoice == 1){ledChange(led[1]);}
				if (l == 10 && ledchoice == 2){ledChange(led[2]);}
				if (l == 10 && ledchoice == 3){ledChange(led[3]);}
				if(l == 10 && ledchoice == 4){led_menu_selected=false;keypad(menu_win,TRUE);keypad(led_menu,FALSE);print_second_menu(second_menu,highlight);refresh(); l= 0;ledchoice=0;}//ledmenuOFF
		}
		
		print_menu(menu_win, highlight);
		refresh();
	}	
	clrtoeol();
	refresh();
	endwin();
}

