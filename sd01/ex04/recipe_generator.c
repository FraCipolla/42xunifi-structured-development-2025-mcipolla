#include "recipe_generator.h"

/*
 * You are building an interactive recipe generator that creates recipes based on the user’s
 * current ingredients and taste profile, repeating the generation process until the user approves
 * the result. The program should:
 * 1. Fetch the current fridge ingredients.
 * 2. Fetch the user’s taste profile.
 * 3. Iteratively generate a recipe candidate:
 * • Produce a new recipe.
 * • Ask for user approval.
 * • Repeat until approved.
 * 4. Return the final approved recipe.
*/

struct Recipe *create_custom_recipe(void) {
    struct Ingredients *ingredients = get_current_ingredients();
    struct TasteProfile *taste = get_user_taste_profile();
    struct Recipe *recipe = NULL;

    if (ingredients && taste) {
        while(42) {
            recipe = create_recipe(ingredients, taste);
            if (!recipe || get_user_approval(recipe)) {
                break;
            }
            free_recipe(recipe);
        }
    }
    if (ingredients) free_ingredients(ingredients);
    if (taste) free_taste_profile(taste);
    return recipe;
}