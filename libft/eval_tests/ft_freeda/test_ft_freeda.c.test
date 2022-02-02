/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_freeda.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:17:19 by jniemine          #+#    #+#             */
/*   Updated: 2021/11/30 17:46:10 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "unity.h"
#include "libft.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_ft_freeda(void)
{
	char *s = "Happy boy is taking a walk with a laughing dog.";
	char **res = ft_strsplit(s, ' ');
	ft_freeda((void ***)(&res), 10);
	
	printf("%p\n", res);
//	printf("%p\n", res[0]);
//	printf("%p\n", res[9]);
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
	RUN_TEST(test_ft_freeda);
    return UNITY_END();
}
