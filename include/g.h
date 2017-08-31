
#define BUFF_SIZE 1
#define D(doubl) (doubl):O_TRUNC?O_APPEND

#define MIN(x,y) ((x) < (y) ? (x) : (y))
#define MAX(x,y) ((x) > (y) ? (x) : (y))

typedef struct	s_data {
	char	*str;
	int		len;
	int		pointeur;
	int		pos_start;
}				t_data;

typedef struct	s_fd{
	int fd_stn[2];
	int fd_err[2];
}				t_fd;

char	*saisie(void);
void	clean(t_data *blk);
void	yolo(int dir, int y);
t_data	*t_dat_init(void);
void	point(t_data *blk, int fg);
void	set_t_data_pointeur(t_data *blk, int inc);

char	*recule(t_data *blk);
int		ft_alloc(t_data *data, char *ajout);

int		pass_canonique(void);

void	move_simple(char *s, t_data *blk);
void	move_simple_depl(char *s, t_data *blk);
