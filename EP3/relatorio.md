# **MAC0422 - SISTEMAS OPERACIONAIS**

## Relatório EP3

------

### **Washington Luiz - 10737157**

### **Ygor Tavela Alves - 10687642**



## 1. **Política de alocação**

Abaixo descrevemos a implementação da chamada de sistema ***memalloc***, cuja função é alterar a estratégia de alocação de memória do sistema.  

- Parâmetros: **type** da política de alocação de memória do sistema, pode ser definido como **WORST_FIT** ou **FIRST_FIT** (macros definidades em */usr/src/include/unistd.h*);

- Rotina:
   1. Em *src/lib/posix/_memalloc.c* (protótipo no header *unistd.h*) é criado uma nova *message* **m**, contendo o **type** da política de alocação de memória e o **EUID** do processo de quem chamou a *syscall*;
   2. Envia **m** ao *process manager* (**MM**), indicando a rotina **MEMALLOC** deve ser executada usando ***_syscall(MM, MEMALLOC, &m)***. Sendo a macro **MEMALLOC** definida em *src/include/minix/callnr.h* e, mapeada na tabela de rotinas do *process manager* em *src/server/pm/table.c*, com rotina correspondente a **do_memalloc**;
   3. Chama a rotina **do_memalloc** (*/usr/src/servers/pm/alloc.c*) que extrai os parâmetros de **m** e, verifica se o processo que a chamou é o *effective user* **root**. Se for o caso, é alterado o valor da variável local **alloc_type** para o **type** recebido pela *message*, alterando o comportamento da função *alloc_mem* descrito abaixo.
   
- Função *alloc_mem* (*/usr/src/servers/pm/alloc.c*):

   Para alternar a política de alocação de memória do sistema, utilizamos a variável **alloc_type**. Por padrão, definimos ela como **FIRST_FIT**, assim a função irá sempre utilizar o primeiro *hole* adequado para um processo, ou seja, ao iterar a lista de *hole*, caso na iteração atual o *hole* tenha tamanho suficiente para alocar o processo desejado então, a função retorna o início do endereço do bloco de memória para alocar tal processo . Caso o tipo seja alternado para **WORST_FIT**, iteramos **toda** lista de *holes* em busca do maior disponível e, assim, caso este *hole* tenha tamanho suficiente para comportar o processo desejado, retornamos o início do bloco de memória correspondente a tal *hole* de maior tamanho. 



## 2. **Mapa da memória**

Em */usr/local/src* encontra-se o código fonte do programa **memorymap**, o qual é responsável por exibir na saída padrão um "mapa" da memória. Sua implementação é específicada abaixo:

- Utilizamos a *system call* ***getsysinfo*** para obter uma cópia da tabela de processos *mproc*, assim iteramos um total de **NR_PROCS** processos da tabela e, caso o processo esteja ativo, printamos em uma linha seu **pid**, início do segmento de memória do **Text** como posição inicial e, posição final, sendo a soma do inicio do segmento de memória **Stack** com o seu tamanho total. Vale destacar que utilizamos o endereço de memória físico dos segmentos de memória do processo. 
- Novamente, para imprimir a quantidade total de memória livre, utilizamos a *syscall* ***getsysinfo*** para obter uma cópia da struct *pm_mem_info*. Essa struct contém uma lista dos segmentos de memória livre, a qual percorremos e somamos cada tamanho de segmento para obter o total, que é medido em *phys_clicks*.