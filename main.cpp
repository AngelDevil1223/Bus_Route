#include "utils.h"

int main(int argc, char **argv)
{
    DIR* FD;
    struct dirent* in_file;
    FILE    *common_file;
    FILE    *entry_file;
    char    buffer[BUFSIZ];
    char address[500];
    int total_lines = 0;

    common_file = fopen("tmp.bin", "w");
    if (common_file == NULL)
    {
        fprintf(stderr, "Error : Failed to open common_file - %s\n", strerror(errno));
        return 1;
    }

    if (NULL == (FD = opendir (argv[1])))
    {
        fprintf(stderr, "Error : Failed to open input directory - %s\n", strerror(errno));
        fclose(common_file);
        return 1;
    }
    while ((in_file = readdir(FD)))
    {
        if (!strcmp (in_file->d_name, "."))
            continue;
        if (!strcmp (in_file->d_name, ".."))
            continue;
        sprintf(address, "%s\\%s", argv[1], in_file->d_name );
        entry_file = fopen(address, "r");
        if (entry_file == NULL)
        {
            fprintf(stderr, "Error : Failed to open entry file - %s\n", strerror(errno));
            fclose(common_file);
            return 1;
        }
        int line;
        char time[150], stop[150];
        char tmp;
        int blank_flag=0;
        do{
         tmp = getc(entry_file);
         if(tmp != EOF)
         {
           if(tmp == '\n')
           {
            blank_flag++;
                if(blank_flag==2)
                {
                    fprintf(common_file,"NONE\n");
//                    printf("%c", tmp);
                    blank_flag = 0;
                }
                else
                {
                fprintf(common_file,"%c", tmp);
//                printf("%c", tmp);
                }
            }
            else
            {
             fprintf(common_file,"%c", tmp);
//             printf("%c", tmp);
             blank_flag=0;
            }
         }
         }while(tmp!=EOF);
        fprintf(common_file,"\nNEW\n");
//        printf("\n---------------\n");
        fclose(entry_file);
        }
    fclose(common_file);

	//To display various start time
	std::fstream display;
	display.open("tmp.bin", std::ios::in);
	string line;
	vector<string> vec;
	vec.clear();
	cout<<"Starting time with Line Number:-\n";
	while(getline(display,line))
	{
		if(line=="NEW")
		{
			for(int i=0;i<vec.size()-1;i++)
					cout<<vec[i]<<"\n";
			cout<<"\n\n";
			vec.clear();
		}
		else if(line=="NONE")
		{
			if(vec.size()==1)
				cout<<"Line Number : "<<vec[0]<<"\n";
			else
				for(int i=0;i<vec.size()-1;i++)
					cout<<vec[i]<<"\n";
			vec.clear();
			cout<<"\n";
		}
		else
			vec.push_back(line);
	}
	display.close();

    string start_stop, end_stop, departure;
    printf("Start stop: ");
    cin>>start_stop;
    std::cout<<start_stop<<std::endl;

    printf("End stop: ");
    cin>>end_stop;
    std::cout<<end_stop<<std::endl;

    printf("Departure Time: ");
    cin>>departure;
    std::cout<<departure<<std::endl;

	std::string curr_line;//current line

	std::fstream f;
	f.open("tmp.bin", std::ios::in);
	std::fstream res;
	res.open(argv[2], std::ios::app);
	int start=0,route_number=-1,result=0;
	size_t pos = 0;
	vector<string> stops;
	while(getline(f,curr_line))
	{
		if(curr_line.compare("NONE") == 0)
		{
			start=0;
		}
    	else if ((pos = curr_line.find(" ")) != string::npos) {
			if(difference(departure, curr_line.substr(0, pos)).compare("0:0")==0 && start_stop.compare(curr_line.substr(pos+1))==0)//finding the difference of 2 times
			{
//				cout<<"Start point found!\n";
				start=1;
			}
			else if(end_stop.compare(curr_line.substr(pos+1))==0 && (start==1))//finding the difference of 2 times
			{
//				cout<<"End point found!\n\n";
				res<<"From : "<<start_stop<<"\nTo : "<<end_stop<<"\n";
				res<<"Line number : "<<route_number<<"\n";
				stops.push_back(curr_line.substr(pos+1));
				res<<"Time of Departure : "<<departure<<"\n";
				res<<"Time of Arrival : "<<curr_line.substr(0,pos)<<"\n";
				res<<"Travel time : "<<difference(departure,curr_line.substr(0,pos))<<"(Hours and Minutes)\n";
				res<<"List of stops : ";
				for(int i=0;i<stops.size();i++)
				{
					if(i==stops.size()-1)
						res<<stops[i];
					else
						res<<stops[i]<<" -> ";
				}
				res<<"\n\n";
				stops.clear();
				start=0;
				result=1;
			}
			if(start==1)
				stops.push_back(curr_line.substr(pos+1));
		}
	    else if(curr_line.compare("NEW") == 0)
		{
//			cout<<"NEW\n";
			start=0;
		}
		else
		{
			route_number = stoi(curr_line);
		}
	}
	if(result==0)
	{
		res<<"From : "<<start_stop<<"\nTo : "<<end_stop<<"\n";
		res<<"Time of Departure : "<<departure<<"\n";
		res<<"No route found!\n\n";
	}
	f.close();
	res.close();
    return 0;
}
