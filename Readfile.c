// Вставляю сюда все файлы из примера решения и пишу пояснения, если что непонятно спрашивай
// Первым делом он пишет 

#ifndef HEADERS_H// если этот файл еще не запускался
# define HEADERS_H// запустить этот файл

# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# define BUF_FIRST 5
# define TRUE 1
# define FALSE 0

typedef struct		s_list
{
	char				data;
	struct s_list		*next;
}					t_list;

char				g_empty;
char				g_obstacle;
char				g_filled;
int					g_rows;
int					g_col;
int					g_maxsize;
int					g_maxposition;

int					is_valid_rows(char *str);
char				*insert_square(char *str);
int					is_valid_first_line(char *str, int size);
char				*ft_import_file(char *file);
char				*ft_import_stdin(void);
int					ft_strcmp(char *s1, char *s2);
void				ft_putchar(char c);
void				ft_putstr(char *str);
void				ft_putnbr(int nb);
int					is_number(char c);
void				solve_grid(char *str);
char				*ft_concat_list(t_list *list, int len);
void				ft_push_list(t_list **node, char c);
t_list				*ft_create_node(char c);
#endif

#include "headers.h"//чтобы работали функции

int		ft_import_first_line(int fd)//создаем ф-ю которая принимает инт и выдает инт в переменной fd
{
	t_list	*list;//
	char	buf;//
	int		str_size;//

	list = NULL;//
	str_size = 0;//
	while (read(fd, &buf, 1) > 0)//
	{
		str_size++;
		ft_push_list(&list, buf);
		if (buf == '\n')//
			break ;//
	}
	if (is_valid_first_line(ft_concat_list(list, str_size), str_size))//
		return (1);
	return (0);//
}

char	*ft_import_stdin(void)//
{
	t_list	*list;
	char	buf;
	int		str_size;//

	if (ft_import_first_line(0))//
	{
		list = NULL;//
		str_size = 0;
		while (read(0, &buf, 1) > 0)//
		{
			if (buf != g_empty && buf != g_obstacle && buf != '\n')//
				return (NULL);//
			ft_push_list(&list, buf);//
			str_size++;//
		}
		return (ft_concat_list(list, str_size));//
	}
	return (NULL);//
}

char	*ft_import_file(char *file)//
{
	t_list	*list;
	char	buf;
	int		str_size;
	int		fd;//

	fd = open(file, O_RDONLY);//
	if (ft_import_first_line(fd))//
	{
		list = NULL;
		str_size = 0;
		while (read(fd, &buf, 1) > 0)//
		{
			if (buf != g_empty && buf != g_obstacle && buf != '\n')//
				return (NULL);
			ft_push_list(&list, buf);//
			str_size++;
		}
		close(fd);//
		return (ft_concat_list(list, str_size));//
	}
	return (NULL);
}
