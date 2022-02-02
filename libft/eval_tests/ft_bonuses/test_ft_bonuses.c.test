#include <stdlib.h>
#include "unity.h"
#include "libft.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_ft_lstnew(void) {
	printf("\n-----ft_lstnew-----\n");
	// With correct input and size
   	char a[20] = "Me fancy fine words";
	t_list *res = ft_lstnew((void *)a, sizeof(a));
	TEST_ASSERT_EQUAL_STRING (a, (char *)(*res).content);
	TEST_ASSERT_EQUAL_INT (20, (*res).content_size);
	TEST_ASSERT_EQUAL_PTR (NULL, (*res).next);
	TEST_ASSERT (a != (*res).content);
	// With NULL content
	res = ft_lstnew(NULL, sizeof(a));
	TEST_ASSERT_NULL ((char *)(*res).content);
	TEST_ASSERT_EQUAL_INT (0, (*res).content_size);
	TEST_ASSERT_NULL ((*res).content);
	TEST_ASSERT (a != (*res).content);
	// With contetn size smaller than string
	char a2[5];
	memset(a2, 'x', sizeof(a2));
	memset(a2, 'o', 3);
	res = ft_lstnew((void *)a2, 3);
	TEST_ASSERT_EQUAL_MEMORY (a2, (char*)(*res).content, 3); 
	TEST_ASSERT_EQUAL_INT (3, (*res).content_size);
	TEST_ASSERT_NULL ((*res).next);
	TEST_ASSERT (a != (*res).content);

}
//Function for testing lstdelone
void ft_memndel(void *del, size_t size)
{
	free (del);
	size = 0;
	size += 1;
}
void test_function_lstdelone(void) {
	printf("\n-----ft_lstdelone-----\n");
	char a[] = "To NULL or NOTTONULL?!"; 
    t_list *to_null = ft_lstnew(a, 25);
	ft_lstdelone(&to_null, ft_memndel);
	TEST_ASSERT_NULL (to_null);
	//Call with NULL function
	t_list *null = ft_lstnew("Hello", 6);
	ft_lstdelone(&null, NULL);
	TEST_ASSERT_NOT_NULL (null);
}
//Testing ft_lstdel
void test_function_ft_lstdel(void)
{
	printf("\n-----ft_lstdel-----\n");
	t_list *head = ft_lstnew("This is a head which is ahead\n", 35);
	t_list *link1 = ft_lstnew("This is link nb 1\n", 30);
	t_list *link2 = ft_lstnew("This is link nb 2\n", 30);
	head->next = link1;
	head->next->next = link2;
	ft_lstdel(&head , ft_memndel);
	TEST_ASSERT_NULL (head);
	TEST_ASSERT_NULL (link1->next);
	TEST_ASSERT_NULL (link2->next);
	//Test with NULL function
	head = ft_lstnew("This is a head which is ahead\n", 35);
	link1 = ft_lstnew("This is link nb 1\n", 30);
	link2 = ft_lstnew("This is link nb 2\n", 30);
	head->next = link1;
	head->next->next = link2;
	ft_lstdel(&head, NULL);
	TEST_ASSERT_NOT_NULL (head);
	TEST_ASSERT_NOT_NULL (link1->next);
	TEST_ASSERT_NULL (link2->next);
}	
void test_ft_lstadd(void)
{
	t_list *head = ft_lstnew("This is the first head.", 30);
	t_list *new_head = ft_lstnew("I want to be head in place of head!!", 40); 
	t_list *displaced_head = head;
	ft_lstadd(&head, new_head);
	//Test that new head is pointing to displaced one
	TEST_ASSERT_TRUE (new_head->next == displaced_head);
	//Test that contents are unchanged
	TEST_ASSERT_EQUAL_STRING(displaced_head->content, new_head->next->content);
	TEST_ASSERT_EQUAL_STRING(new_head->content, head->content);
	//Test that displaced.next is pointing to NULL
	TEST_ASSERT_NULL(displaced_head->next);
	//Test with NULL params
	ft_lstdel(&new_head, ft_memndel);
	head = ft_lstnew("This is the first head.", 30);
	new_head = ft_lstnew("I want to be head in place of head!!", 40); 
	displaced_head = head;
	//Does not cause a crash, but adding pointer to NULL as last link can cause trouble latert on...
	t_list *to_null = NULL;
	t_list *old = to_null;
	ft_lstadd(&to_null, head);
	TEST_ASSERT_TRUE (head == to_null);
	TEST_ASSERT_TRUE (head->next == old);
	//These should be protected
	ft_lstadd(NULL, NULL);
	ft_lstadd(&head, NULL);
}
void ft_catcontent(t_list *dog)
{
	char *cat = "cat";

	(*dog).content = cat;
}
void test_ft_lstiter(void)
{
	t_list *head = ft_lstnew("Dog", 4);
	t_list *new_head = ft_lstnew("Dog", 4); 
	t_list *new_head_head = ft_lstnew("Dog", 4);
	head->next = new_head;
	new_head->next = new_head_head;
	ft_lstiter(head, ft_catcontent);

	TEST_ASSERT_EQUAL_STRING("cat", head->content);
	TEST_ASSERT_EQUAL_STRING("cat", new_head->content);
	TEST_ASSERT_EQUAL_STRING("cat", new_head_head->content);
	//Crash test with NULL params
	ft_lstiter(NULL, ft_catcontent);
	ft_lstiter(head, NULL);
	ft_lstiter(NULL, NULL);
}

t_list *ahead(t_list *link)
{
	t_list *new_link;

	new_link = ft_lstnew(link->content, link->content_size);
	(*new_link).content = "ahead";
	return (new_link);
}
void test_ft_lstmap(void)
{
	t_list *head = ft_lstnew("I am the head", 50);
	t_list *new_head = ft_lstnew("I want to be head in place of head", 50); 
	t_list *new_head_head = ft_lstnew("I want to be ahed of the one placing the head", 50);
	head->next = new_head;
	new_head->next = new_head_head;
	t_list *orig_new_head = new_head;
	t_list * res = ft_lstmap(head, ahead);

	//Old list should have old address
	TEST_ASSERT_TRUE(head->next == orig_new_head);
	//Fresh list should have different content
	TEST_ASSERT_EQUAL_STRING("ahead", res->content);
	TEST_ASSERT_EQUAL_STRING("ahead", res->next->content);
	TEST_ASSERT_EQUAL_STRING("ahead", res->next->next->content);

	//Fresh list should have different addresses
	TEST_ASSERT_FALSE (head == res);
	TEST_ASSERT_FALSE (head->next == res->next);
	//NULL checkfault check
	ft_lstmap(NULL, ahead);
	ft_lstmap(head, NULL);
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
//	RUN_TEST(test_ft_lstnew);
 //	RUN_TEST(test_function_lstdelone);
 //	RUN_TEST(test_function_ft_lstdel);
// 	RUN_TEST(test_ft_lstadd);
//	RUN_TEST(test_ft_lstiter);
	RUN_TEST(test_ft_lstmap);
    return UNITY_END();
}
