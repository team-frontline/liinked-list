Enter this command in Terminal while you are in the Source Folder (commands worked with ubutu 18.04)

For Serial Program
------------------
To compile: gcc -o serial_linked_list serial_linked_list.c -lm
To execute: ./serial_linked_list <n> <m> <m_member> <m_insert> <m_delete>


For One-Mutex Program
------------------
To compile: gcc -pthread -o test_mutex one_mutex_linked_list.c
To execute: ./serial_linked_list <n> <m> <m_member> <m_insert> <m_delete>


For Read-Write lock Program
------------------
To compile: gcc -pthread read_write_linked_list read_write_linked_list.c
To execute: ./read_write_linked_list <n> <m> <thread_count> <m_member> <m_insert> <m_delete>


