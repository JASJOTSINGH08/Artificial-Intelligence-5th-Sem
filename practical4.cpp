#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
#include<set>

#define MATRIX_SIZE 28

//create adj matrix func
void createAdjMatrix(const std::string &text, int matrix[MATRIX_SIZE][MATRIX_SIZE], const std::unordered_map<char,int>&charIndexMap){
    for( size_t i = 0 ; i < text.size()-1 ; i++){
        char current = text[i];
        char next = text[i+1];

        if (charIndexMap.find(current)!=charIndexMap.end() && charIndexMap.find(next)!=charIndexMap.end()){
            int currentIndex = charIndexMap.at(current);
            int nextIndex = charIndexMap.at(next);
            matrix[currentIndex][nextIndex] = 1;
            matrix[nextIndex][currentIndex] = 1; // assumed undirected 
        }
    }
}

// func for bfs starting from 'e'
void bfs(const int matrix[MATRIX_SIZE][MATRIX_SIZE], const std::unordered_map<char,int> &charIndexMap){
    std::queue<int> q;
    std::vector<bool> visited(MATRIX_SIZE, false);

    int startIndex = charIndexMap.at('e');
    while(!q.empty()){
        int current = q.front();
        q.pop();
        std::cout << char(current + 'a') << " ";

        for (int i = 0; i < MATRIX_SIZE; i++){
            if(matrix[current][i] && !visited[i]){
                visited[i] = true;
                q.push(i);
            }
        }
    }
    std::cout << std::endl;
}

int main(){
    std::string text = "Everything was in confusion in the Oblonskys' house. The wife had discovered that the husband was carrying on an intrigue with a French girl, who had been a governess in their family, and she had announced to her husband that she could not go on living in the same house with him. This position of affairs had now lasted three days, and not only the husband and wife themselves, but all the members of their family and household, were painfully conscious of it. Every person in the house felt that there was no sense in their living together, and that the stray people brought together by chance in any inn had more in common with one another than they, the members of the family and household of the Oblonskys. The wife did not leave her own room, the husband had not been at home for three days. The children ran wild all over the house; the English governess quarreled with the housekeeper, and wrote to a friend asking her to look out for a new situation for her; the man-cook had walked off the day before just at dinner time; the kitchen-maid, and the coachman had given warning. Three days after the quarrel, Prince Stepan Arkadyevitch Oblonsky--Stiva, as he was called in the fashionable world--woke up at his usual hour, that is, at eight o'clock in the morning, not in his wife's bedroom, but on the leather-covered sofa in his study. He turned over his stout, well-cared-for person on the springy sofa, as though he would sink into a long sleep again; he vigorously embraced the pillow on the other side and buried his face in it; but all at once he jumped up, sat up on the sofa, and opened his eyes. Stepan Arkadyevitch's eyes twinkled gaily, and he pondered with a smile. There was a great deal more that was delightful, only there's no putting it into words, or even expressing it in one's thoughts awake. And noticing a gleam of light peeping in beside one of the serge curtains, he cheerfully dropped his feet over the edge of the sofa, and felt about with them for his slippers, a present on his last birthday, worked for him by his wife on gold-colored morocco. And, as he had done every day for the last nine years, he stretched out his hand, without getting up, towards the place where his dressing-gown always hung in his bedroom. And thereupon he suddenly remembered that he was not sleeping in his wife's room, but in his study, and why: the smile vanished from his face, he knitted his brows. Most unpleasant of all was the first minute when, on coming, happy and good-humored, from the theater, with a huge pear in his hand for his wife, he had not found his wife in the drawing-room, to his surprise had not found her in the study either, and saw her at last in her bedroom with the unlucky letter that revealed everything in her hand. She, his Dolly, forever fussing and worrying over household details, and limited in her ideas, as he considered, was sitting perfectly still with the letter in her hand, looking at him with an expression of horror, despair, and indignation. And at this recollection, Stepan Arkadyevitch, as is so often the case, was not so much annoyed at the fact itself as at the way in which he had met his wife's words. There happened to him at that instant what does happen to people when they are unexpectedly caught in something very disgraceful. He did not succeed in adapting his face to the position in which he was placed towards his wife by the discovery of his fault. Instead of being hurt, denying, defending himself, begging forgiveness, instead of remaining indifferent even--anything would have been better than what he did do--his face utterly involuntarily (reflex spinal action, reflected Stepan Arkadyevitch, who was fond of physiology)--utterly involuntarily assumed its habitual, good-humored, and therefore idiotic smile. This idiotic smile he could not forgive himself. Catching sight of that smile, Dolly shuddered as though at physical pain, broke out with her characteristic heat into a flood of cruel words, and rushed out of the room. Since then she had refused to see her husband.";

    std::set<char>uniqueChars;
    std::unordered_map<char,int> charIndexMap;

    //extracting first 28 unique characters
    for(char c : text){
        if(uniqueChars.size() >= MATRIX_SIZE) break;
        if (isalpha(c)){
            uniqueChars.insert(c);
        }    
    }

    int index = 0;
    for ( char c : uniqueChars){
        charIndexMap[c] = index++;
    }

    //initialize adj matrix
    int matrix[MATRIX_SIZE][MATRIX_SIZE] = {0};

    //create adj matrix
    createAdjMatrix(text, matrix, charIndexMap);

    //display adj matrix
    std::cout<<"Adjacency Matrix (28 X 28 ):\n";

    for(int i = 0; i < MATRIX_SIZE ; i++){
        for(int j = 0; j < MATRIX_SIZE ; j++){
            std::cout<<matrix[i][j]<< " ";
    }
    std::cout<<std::endl;
}

//performing bfs starting from 'e'
bfs(matrix, charIndexMap);

return 0;

}